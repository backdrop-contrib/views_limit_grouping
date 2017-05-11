<?php

/**
 * @file views-limit-grouping.tpl.php
 * Basically, just a copy of views-view-unformatted.tpl.php.
 */
?>
<div class="views-limit-grouping-group">
  <?php if (!empty($title)): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php foreach ($rows as $row_count => $row): ?>
    <div class="views-row views-row-<?php print $zebra; ?> <?php print $classes; ?>">
      <?php print $row; ?>
    </div>
  <?php endforeach; ?>
</div>