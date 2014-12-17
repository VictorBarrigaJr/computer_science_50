<?
    // stock data to to dysplay
    print("Name: " . $_POST["name"]);
    print("<br>");
    print("Symbol: " . $_POST["symbol"]);
    print("<br>");
    print("Price: " . number_format($_POST["price"], 2)); 
    print("<br>");

?>
