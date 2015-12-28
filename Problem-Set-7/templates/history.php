<div>
    <?php if (!empty($history)): ?>
        <table class="table table-striped cs50">
            <thead>
                <tr>
                    <td style="text-align: left;"><b>Date / Time</b></td>
                    <td style="text-align: center;"><b>Transaction</b></td>
                    <td style="text-align: left;"><b>Symbol</b></td>
                    <td style="text-align: right;"><b>Shares</b></td>
                    <td style="text-align: right;"><b>Price</b></td>
                    <td style="text-align: right;"><b>Transaction Value</b></td>
                </tr>
            </thead>

            <tbody>
                <?php foreach ($history as $row): ?>
                    <tr>
                        <td style="text-align: left;"><?= $row["trans_date"] ?></td>
                        <td style="text-align: center;"><?= $row["transaction"] ?></td>
                        <td style="text-align: left;"><?= $row["symbol"] ?></td>
                        <td style="text-align: right;"><?php print($row["shares"] == 0 ? "" : $row["shares"]) ?></td>
                        <td style="text-align: right;"><?php print($row["share_price"] == 0 ? "" : "$" . $row["share_price"]) ?></td>
                        <td style="text-align: right;"><?= "$" . $row["trans_value"] ?></td>
                    </tr>
                <?php endforeach ?>
            </tbody>
        </table>
    <?php else: ?>
        No transaction history.
    <?php endif ?>
</div>
