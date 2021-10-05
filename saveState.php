<?php
    $server = "localhost";
    $username = "root";
    $password = "";
    $db = "test";

    $conn = new mysqli($server, $username, $password, $db);

    $windowId = $_GET['windowId'];
    $state = $_GET['state'];

    echo "Window ID:".$windowId." & State: ".$state;

    $sql = "INSERT INTO data SET windowId='".$windowId."', state='".$state."';";

    $conn->query($sql);
?>