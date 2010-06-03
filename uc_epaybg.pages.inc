<?php
// $Id$

/**
 * @file
 * ePay.bg menu callbacks.
 *
 * @author Martin Martinov <matix.bg@gmail.com>
 */

/**
 * Payment done page callback.
 */
function uc_epaybg_payment_done() {
  $hash_hmac = _get_hash_hmac();

  $ENCODED  = $_POST['encoded'];
  $CHECKSUM = $_POST['checksum'];
  
  if ((!isset($ENCODED)) || (!isset($CHECKSUM))) {
    exit();
  }
  // Secret word with which merchant make CHECKSUM on the ENCODED packet
  $secret = variable_get('uc_epaybg_secret_key', '');
  $hmac = $hash_hmac('sha1', $ENCODED, $secret); // SHA-1 algorithm REQUIRED

  if ($hmac == $CHECKSUM) {
    // Check if the received CHECKSUM is OK

    $data = base64_decode($ENCODED);

    $lines_arr = split("\n", $data);
    foreach ($lines_arr as $line) {
     if (preg_match("/^INVOICE=(\d+):STATUS=(PAID|DENIED|EXPIRED)(:PAY_TIME=(\d+):STAN=(\d+):BCODE=([0-9a-zA-Z]+))?$/", $line, $regs)) {
         $invoice  = $regs[1]; // order_id
         $status   = $regs[2];
         $pay_date = $regs[4]; // if PAID
         $stan     = $regs[5]; // if PAID
         $bcode    = $regs[6]; // if PAID
      }
    }
    if (isset($invoice) && $status == 'PAID') {
      /*
      $data = db_fetch_object(
        db_query("SELECT * FROM {uc_epaybg_transaction} WHERE txn_id = %d", $invoice)
      );
      */
      $order = uc_order_load($invoice);
      $amount = $order->order_total * variable_get('uc_epaybg_rate', '1.00');
      if ($order === FALSE || uc_order_status_data($order->order_status, 'state') != 'in_checkout') {
        echo "INVOICE:{$invoice}:STATUS=NO". PHP_EOL;
        exit();
      }
      $description = t(
        'Payment from order number %order_id was accepted. STAN: !stan; pay_date: !pay_date; BCODE: !bcode;',
        array('%order_id' => $invoice, '!stan' => $stan, '!pay_date' => $pay_date, '!bcode' => $bcode )
      );
      db_query(
        "UPDATE {uc_epaybg_transaction} SET description = '%s' WHERE txn_id = %d",
        $description,
        $invoice
      );
      uc_payment_enter($invoice, 'epaybg', $amount, $order->uid, NULL, $description);
      uc_cart_complete_sale($order);
      uc_order_comment_save($invoice, 0,
        t('A payment with Transaction ID: @txn_id for @amnt has been accepted.',
          array('@txn_id' => $invoice, '@amnt' => $amount)),
        'order',
        'payment_received'
      );
      unset($_SESSION['cart_order'], $_SESSION['do_complete']);
      (is_numeric($order->uid) ? uc_cart_empty($order->uid) : uc_cart_empty(uc_cart_get_id()));

      // give an answer to the requester (ePay.bg)
      $response = "INVOICE={$invoice}:STATUS=OK" . PHP_EOL;
      echo $response;
    }
    else if ($status === 'DENIED') {
      // log that the payment was denied
    }
    else if ($status === 'EXPIRED') {
      // log that the payment expired
    }
  }
}

/**
 * Payment cancelled page callback.
 */
function uc_epaybg_payment_cancel() {
  unset($_SESSION['cart_order']);

  drupal_set_message(
    t('Your ePay.bg payment was cancelled. Please feel free to continue shopping or contact us for assistance.')
  );

  drupal_goto(variable_get('uc_paypal_wps_cancel_return_url', 'cart'));
}
