<?php

    // configuration
    require("../includes/config.php"); 

    // query current user shares
    $rows = query("SELECT symbol, shares FROM shares WHERE user_id = ?", $_SESSION["id"]);
    
    // from spec, array to store share info, combines names and prices from lookup.
    $positions = [];
    foreach ($row as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
            ];
        }    
    } 
    
    // user balance
    $cash = query("SELECT username, cash FROM users WHERE id = $id");
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio" "positions" => $positions, "cash"=> $cash]);

?>
