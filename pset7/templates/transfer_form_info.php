<?php
    // Confirmation of transfer
    print("<strong>Your order has been filled.</strong>");
    print("<br>");
    print("<br>");
    print("Transfer from account: " . $_POST["from_account"] );
    print("<br>");
    print(" to account: " . $_POST["to_account"]); 
    print("<br>");
    print("for: " . "$" . number_format($_POST["amount"], 2)); 
    print("<br>");
?>

