<?php
$pin_state_file = __DIR__ . '/pin_state.txt';

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    if (file_exists($pin_state_file)) {
        $pin_state = file_get_contents($pin_state_file);
        echo $pin_state;
        exit; // Salir para evitar imprimir el HTML en caso de GET
    } else {
        echo "File not found";
    }
} elseif ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['action'])) {
    $action = $_POST['action'];

    if ($action == 'on') {
        file_put_contents($pin_state_file, 'ON');
       // echo "ON";
    } elseif ($action == 'off') {
        file_put_contents($pin_state_file, 'OFF');
        //echo "OFF";
    } else {
        echo "Invalid action";
    }

    // Después de procesar la solicitud POST, incluir el contenido HTML completo
    include 'index.html';
} else {
    http_response_code(400); // Bad Request
    echo "Invalid request";
}
?>