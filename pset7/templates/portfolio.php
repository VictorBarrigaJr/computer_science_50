<div>  
    <div id="welcome_message">
        <?php
            print("Welcome back, " . $cash[0]["username"] .". Your current balance is " . sprintf("%.2f", $cash[0]["cash"]) .".");
        ?>
    </div>
    <table id="display_portfolio">
        <?php
            print("<tr>");
                print("<th>Name</th>");
                print("<th>Symbol</th>");
                print("<th>Shares</th>");
                print("<th>Price</th>");
                print("<th>Balance</th>");
            print("<tr>");
            
            foreach ($positions as $position)
            {
                print("<tr>");
                    print("<td>" . $position["name"] . "</td>");
                    print("<td>" . $position["symbol"] . "</td>");
                    print("<td>" . $position["shares"] . "</td>");
                    print("<td>" . $position["price"] . "</td>");
                    print("<td>" . $position["total"] . "</td>");
                print("<tr>");
            }
        ?>
<div>
    <a href="logout.php">Log Out</a>
</div>
