<?php

/**
 * Implements hook_views_plugins().
 */
 
function views_limit_grouping_views_plugins() {
  return array(
    'style' => array(
      'grouping_limit' => array(
        'title' => t('Grouping Field (with Limit)'),
        'help' => t('Limit the number of rows for each grouping field'),
        'handler' => 'views_limit_grouping_style_plugin',
        'theme' => 'views_limit_grouping',
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}


/**
 * Preprocess variables for Views Grouping Limit
 */
 
function template_preprocess_views_limit_grouping(&$variables) {
  $view = $variables['view'];
  $rows = $variables['rows'];
  $style = $view->style_plugin;
  $options = $style->options;

  $variables['row_classes'] = array();
  $default_row_class = isset($options['default_row_class']) ? $options['default_row_class'] : FALSE;
  $row_class_special = isset($options['row_class_special']) ? $options['row_class_special'] : FALSE;
  // Set up striping values.
  $count = 0;
  $max = count($rows);
  foreach ($rows as $id => $row) {
    $count++;
    $variables['row_classes'][$id] = array();
    if ($default_row_class) {
      $variables['row_classes'][$id][] = 'views-row';
      $variables['row_classes'][$id][] = 'views-row-' . $count;
    }
    if ($row_class_special) {
      $variables['row_classes'][$id][] = ($count % 2 ? 'odd' : 'even');
      if ($count == 1) {
        $variables['row_classes'][$id][] = 'first';
      }
      if ($count == $max) {
        $variables['row_classes'][$id][] = 'last';
      }
    }

    if ($row_class = $view->style_plugin->get_row_class($id)) {
      $variables['row_classes'][$id][] = $row_class;
    }
  }
}

