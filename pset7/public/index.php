<?php

    // configuration
    require("../includes/config.php"); 

    // query user's portfolio
    $rows = query("SELECT user_id, symbol, shares FROM user_portfolios WHERE user_id = ?", $_SESSION["id"]);
    
    // create array store data for porfolio table
    $portfolio = [];
    
    // for each user's individual stock type
    foreach ($rows as $row)
    {
        // look up stock info
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $portfolio[] = [
            "name"      =>  $stock["name"],
            "price"     =>  $stock["price"],
            "shares"    =>  $row["shares"],
            "symbol"    =>  $row["symbol"],
            "total"     =>  sprintf("%.2f", $row["shares"] * $stock["price"])
            ];
        
        }
        
        /*
        // look up shares
        $stock["shares"] = $row["shares"];
        // compute total
        $stock["total"] = $row["shares"] * $stock["price"];
        // save row in array
        $portfolio[] = $stock;
        */
    }
    
    // query user's cash
    $users = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "portfolio" => $portfolio, "users" => $users]);  

?>
