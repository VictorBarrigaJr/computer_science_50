<?

// confirmation
require("../includes/config.php");

// if form was submitted
if($_SERVER["REQUEST_METHOD"] == "POST")
{
    // if symbol does not exist apologize, render page
    $_POST = lookup($_POST["symbol"]);
    
    if($_POST === false)
    {
        apologize("Quote not found, please verify symbol, and try again.");
    }
    
    render("../templates/quote.php", ["title" => "Quote"]);
}
// render form
else
{
    render("quote_form.php", ["title" => "Quote"]);
}

?>
