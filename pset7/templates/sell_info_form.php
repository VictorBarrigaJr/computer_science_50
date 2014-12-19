<div>
    <ul class="nav nav-pills">
        <li><a href="index.php">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>

<?
    // Confirmation of sale
    print("<strong>Your order has been filled.</strong>");
    print("<br>");
    print("<br>");
    print("Name: " . $stock_sell["name"]);
    print("<br>");
    print("Symbol: " . $stock_sell["symbol"]);
    print("<br>");
    print("Units sold: " . $_POST["units"]);
    print("<br>");
    print("Fill price: " . "$" . number_format($stock_sell["price"], 2)); 
    print("<br>");
    print("Amount Deposited: " . "$" . number_format($value, 2)); 
    print("<br>");
?>
