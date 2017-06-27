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