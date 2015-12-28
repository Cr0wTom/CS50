<div>
    <h4><?= $stock["name"] ?> (<?= $stock["symbol"] ?>): <b><?= "$" . number_format($stock["price"], 2) ?></b> per share.</h4>
    <br/>
    <a href="buy.php?symbol=<?= $stock["symbol"] ?>"><button class="btn btn-default">Buy this Stock</button></a><br/><br/>
</div>
