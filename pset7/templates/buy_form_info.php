<?
    // Confirmation of sale
    print("<strong>Your order has been filled.</strong>");
    print("<br>");
    print("<br>");
    print("Name: " . $stock_buy["name"]);
    print("<br>");
    print("Symbol: " . $stock_buy["symbol"]);
    print("<br>");
    print("Units purchased: " . $_POST["shares"]);
    print("<br>");
    print("Fill price: " . "$" . number_format($stock_buy["price"], 2)); 
    print("<br>");
    print("Purchase price: " . "$" . number_format($value, 2)); 
    print("<br>");
?>
