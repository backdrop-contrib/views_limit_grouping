<?php

/**
 * @file views-limit-grouping.tpl.php
 * Basically, just a copy of views-view-unformatted.tpl.php.
 */
?>
<div class="views-limit-grouping-group">
  <?php if (!empty($title)): ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <?php foreach ($rows as $row_count => $row): ?>
    <div <?php if (!empty($row_classes[$row_count])) { print 'class="' . implode(' ', $row_classes[$row_count]) . '"';  } ?>>
      <?php print $row; ?>
    </div>
  <?php endforeach; ?>
</div>