<?php

/**
 * @file views-limit-grouping.tpl.php
 *
 * - $title: The title of this group of rows.  May be empty.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are indexed by row number.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 *
 * @ingroup views_templates
 */
?>

<div class="views-limit-grouping-group">
  <?php if (!empty($title)): ?>
    <div class="view-grouping-header"><?php print $title; ?></div>
  <?php endif; ?>
  <?php foreach ($rows as $row_count => $row): ?>
  <div class="view-grouping-content <?php if (!empty($row_classes[$row_count])) { print implode(' ', $row_classes[$row_count]);  } ?>">
      <?php print $row; ?>
    </div>
  <?php endforeach; ?>
</div>
