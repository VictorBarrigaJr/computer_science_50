<?
    // stock data to to dysplay
    print("Symbol: ". $_POST["symbol"]);
    print("<br>");
    print("Name: ". $_POST["name"]);
    print(",br");
    print("Price: ". number_format($_POST["price"], 3)); 

?>
