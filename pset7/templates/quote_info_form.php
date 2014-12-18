<div>
    <ul class="nav nav-pills">
        <li><a href="index.php">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>

<?
    // stock data to to dysplay
    print("Name: " . $_POST["name"]);
    print("<br>");
    print("Symbol: " . $_POST["symbol"]);
    print("<br>");
    print("Price: " . number_format($_POST["price"], 2)); 
    print("<br>");

?>
