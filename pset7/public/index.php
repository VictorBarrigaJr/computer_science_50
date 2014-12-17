<?php

    // configuration
    require("../includes/config.php"); 

    // query current user shares
    $rows = query("SELECT symbol, shares FROM shares WHERE user_id = ?", $_SESSION["id"]);
    
    //
    

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio"]);

?>
