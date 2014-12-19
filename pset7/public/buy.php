<?php

    // configuration
    require("../includes/config.php");
    
    // if form is submitted by user
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate user input
        if(empty($_POST["stock"]))
        {
            apologize("Unable to complete request - please input a stock symbol, and try again.");
        }
        // validate units to sell
        if(empty($_POST["units"]) || !is_numeric($_POST["units"]) || !preg_match("/^\d+$/", $_POST["units"]))
        {
            apologize("Unable to complete request - please verify units to sell, and try again.")
        }
        
        // query stock info from Yahoo, and validate user input
        $stock_buy = lookup($_POST["stock"]);
        $value = $stock_buy * $_POST["stock"];
        if ($buy_stock === false)
        {
            apologize("Unable to complete request - please verify stock symbol, and try agai.") 
        }
        else
        {
          
        }
        
    }
    else
    {
        // render form
        render("buy_form.php",) ["title" => "Buy"];
    }
?>
