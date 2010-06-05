ePay.bg payment module for Ubercart 6

1. Installation
-------------------------------------------------------------------------------
Put the module (uc_epaybg) directory somewhere in sites/all/modules, for
example in sites/all/modules/ubercart/payment/. Then go to admin/build/modules
and enable the module.

2. Settings
-------------------------------------------------------------------------------
At http://yoursite.com/admin/store/settings/payment/edit/methods - set your
merchant MIN, email, secret key and other options. This information must be
taken from your account administration page in ePay.bg.

3. ePay.bg Settings
-------------------------------------------------------------------------------
Copy the value from "URL DONE" field and paste it in your ePay.bg merchant
account in the field 'URL за известяване' - this is very important!

4. Operation
-------------------------------------------------------------------------------
Once you put products in the cart, go to checkout and choose ePay.bg as
payment method. You will be redirected to the ePay.bg processing center, where
you have to authorize and confirm the payment. After this step is completed
you will be sent to your history of orders (user/_uid_/orders). If you refuse
to pay you will be sent back to the page with your shopping cart.


5. Authors:
-------------------------------------------------------------------------------
The original module (for Drupal 5) was contributed by Konstantin Viktorov
http://drupal.org/user/203339

The version for Ubercart 2 (Drupal 6) was developed by Martin Martinov
http://drupal.org/user/207484

While porting the 5.x version to 6.x I've extended it a little bit. I've added
some response codes that now are sent to the ePay.bg server when it sends a
notification for successful or canceled payment to yor server, as it is noted
in the documentation provided by ePay. I have also used the paypal uberacrt
module for reference and I'm plannig to add some more new features and tweaks.
