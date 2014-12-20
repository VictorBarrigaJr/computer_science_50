<form action="transfer.php" method="post">
    <h1 class="form-group-heading">
        Transfer Funds
    </h1>
    <fieldset>
        <div>
            <p>
                Transfer funds <strong>from</strong>:
            </p>
                <select name="from_account">
                    <option value="C$50_Finance_Account">C$50 Finance Account</option>
                    <option value="Checking_Account">Checking Account</option>
                </select>    
        </div>
        <br>
        <div>
            <p>
                Transfer funds <strong>to</strong>:
            </p>
                <select name="to_account">
                    <option value="C$50_Finance_Account">C$50 Finance Account</option>
                    <option value="Checking_Account">Checking Account</option>
                </select>
        </div>
        <br>
            <p>
                Enter dollar <strong>amount</strong>:
                <div class="form-group">
            <input autofocus class="form-control" name="amount" placeholder="Amount" type="text"/>
        </div>
        <br>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Submit</button>
            <!--<button type="cancel" class="btn btn-default"><strong>Cancel</strong></button>-->
        </div>
    </fieldset>
</form>

