ePay.bg payment module for Ubercart 6

1. Installation
Put the module (uc_epaybg) directory somewhere in sites/all/modules, for
example in sites/all/modules/ubercart/payment/. Then go to admin/build/modules
and enable the module.

2. Settings
At http://yoursite.com/admin/store/settings/payment/edit/methods - set your
merchant MIN, email, secret key and other options. This information must be
taken from your account administration page in ePay.bg

3. Operation
Once you put products in the cart, go to checkout and choose ePay.bg as
payment method. You will be redirected to the ePay.bg processing center, where
you have to authorize and confirm the payment. After this step is complete you
will be sent to your history of orders (user/_uid_/orders). If you refuse to
pay, then you will be sent to the page with your cart.
