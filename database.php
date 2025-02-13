<?php
$host = "23.88.73.88";
$user = "u2858692_D9tNOxrkus";
$pass = "nz8V.rGdurPO.W8Xo6LW9awc";
$dbname = "s2858692_db1739453490066";

$conn = new mysqli($host, $user, $pass, $dbname);

if ($conn->connect_error) {
    die("เชื่อมต่อฐานข้อมูลล้มเหลว: " . $conn->connect_error);
}
?>