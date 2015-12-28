<div>
    Current Cash Balance:&nbsp;&nbsp;<b><?= "$" . number_format($user[0]["cash"], 2) ?></b><br/>
    <br/>

    <form action="deposit.php" method="post">
        <fieldset>
            <div class="form-group">
                <input autofocus class="form-control" name="funds" placeholder="Funds to add, e.g. 100.00" type="text"/>
            </div>
            <div class="form-group">
                <button type="submit" class="btn btn-default">Add Funds</button>
            </div>
        </fieldset>
    </form>
</div>
