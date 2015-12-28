<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = array_map('trim', explode(",", urldecode($_GET["geo"])));

    // remove "US" param, as all addresses are US
    if (($index = array_search("US", $places)) !== false) {
        unset($places[$index]);
    }    
    
    // build SQL statement
    $sql = "SELECT * FROM places WHERE ";
    for ($i = 0, $count = count($places); $i < $count; $i++) {
        // if param is numeric, assume a postal code
        if (is_numeric($places[$i])) {
            $sql .= 'postal_code LIKE "' . htmlspecialchars($places[$i], ENT_QUOTES) . '%"';
        } else {
            $sql .= 
                '(place_name  LIKE "' . htmlspecialchars($places[$i], ENT_QUOTES) . '%" OR ' . 
                 (strlen($places[$i]) <= 2 ? 'admin_code1 LIKE "' . htmlspecialchars($places[$i], ENT_QUOTES) . '%" OR ' : "") . 
                 'admin_name1 LIKE "' . htmlspecialchars($places[$i], ENT_QUOTES) . '%")';
        }
        
        if ($i < ($count - 1)) {
            $sql .= " AND ";
        }
    }
    // search database for places matching $_GET["geo"]
    $places = query($sql);
    

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
