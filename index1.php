<?php
session_start();
if (!isset($_SESSION['admin'])) {
    header("Location: login.php");
    exit();
}
include("database.php");
$result = $conn->query("SELECT * FROM items");
?>
<!DOCTYPE html>
<html lang="th">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Panel</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <header>
        <h2>Admin Panel</h2>
    </header>
    <div class="container">
        <h3>เพิ่มไอเทม</h3>
        <form action="process_add.php" method="post">
            <input type="text" name="name" placeholder="ชื่อ" required>
            <input type="text" name="description" placeholder="คำอธิบาย" required>
            <input type="url" name="url" placeholder="URL ดาวน์โหลด" required>
            <input type="text" name="item_code" placeholder="Item Code (ถ้ามี)">
            <button type="submit">เพิ่ม</button>
        </form>

        <h3>รายการไอเทม</h3>
        <table>
            <tr>
                <th>ชื่อ</th>
                <th>คำอธิบาย</th>
                <th>URL</th>
                <th>Item Code</th>
                <th>จัดการ</th>
            </tr>
            <?php while ($row = $result->fetch_assoc()): ?>
                <tr>
                    <td><?= $row['name'] ?></td>
                    <td><?= $row['description'] ?></td>
                    <td><?= $row['url'] ?></td>
                    <td><?= $row['item_code'] ?: "-" ?></td>
                    <td>
                        <a href="edit_item.php?id=<?= $row['id'] ?>">แก้ไข</a> |
                        <a href="delete_item.php?id=<?= $row['id'] ?>">ลบ</a>
                    </td>
                </tr>
            <?php endwhile; ?>
        </table>
    </div>
</body>
</html>