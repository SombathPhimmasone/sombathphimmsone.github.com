<?php
session_start();
include("database.php");

$username = $_POST['username'];
$password = $_POST['password'];

if ($username === "BSB" && $password === "7777") {
    $_SESSION['admin'] = true;
    header("Location: index1.php");
} else {
    echo "ชื่อผู้ใช้หรือรหัสผ่านไม่ถูกต้อง";
}
?>