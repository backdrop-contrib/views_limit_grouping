<?php

/**
 * @file views_grouping_limit_style_plugin.inc
 * Our handler.
 */

class views_limit_grouping_style_plugin extends views_plugin_style {

  /**
   * Overrides parent::options_form().
   *
   * Add our options to the form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    foreach ($form['grouping'] as $index => $info) {
      $defaults = $this->grouping_limit_settings($index);

      $form['grouping'][$index]['grouping-limit'] = array(
        '#type' => 'fieldset',
        '#title' => t('Limit for grouping field Nr.!num', array('!num' => $index + 1)),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#states' => array('invisible' => array(
          "select[name=\"style_options[grouping][{$index}][field]\"]" => array('value' => ''),
        )),
        'grouping-limit' => array(
          '#type' => 'textfield',
          '#title' => t('Items to display:'),
          '#default_value' => isset($defaults['grouping-limit']) ? $defaults['grouping-limit'] : 0,
          '#size' => 6,
          '#element_validate' => array('grouping_validate'),
          '#description' => t('The number of rows to show under each grouping header (only works when "Items to display" in the main view is set to unlimited).'),
        ),
        'grouping-offset' => array(
          '#type' => 'textfield',
          '#title' => t('Offset:'),
          '#default_value' => isset($defaults['grouping-offset']) ? $defaults['grouping-offset'] : 0,
          '#size' => 6,
          '#element_validate' => array('grouping_validate'),
          '#description' => t('The row to start on (<em>0</em> means it will start with first row, <em>1</em> means an offset of 1, and so on).'),
        ),
      );
    }
  }

  /**
   * Overrides parent::render_grouping().
   *
   * This is where the magic happens. Iterate through all of the results, and
   * gather them into groups recursively.
   */
  function render_grouping($records, $groupings = array(), $group_rendered = NULL) {
    // This is for backward compability, when $groupings was a string containing
    // the ID of a single field.
    if (is_string($groupings)) {
      $rendered = $group_rendered === NULL ? TRUE : $group_rendered;
      $groupings = array(array('field' => $groupings, 'rendered' => $rendered));
    }

    // Make sure fields are rendered
    $this->render_fields($this->view->result);

    $sets = array();
    if ($groupings) {
      foreach ($records as $index => $row) {
        // Iterate through configured grouping fields to determine the
        // hierarchically positioned set where the current row belongs to.
        // While iterating, parent groups, that do not exist yet, are added.
        $set = &$sets;
        foreach ($groupings as $info) {
          $field = $info['field'];
          $rendered = isset($info['rendered']) ? $info['rendered'] : $group_rendered;
          $rendered_strip = isset($info['rendered_strip']) ? $info['rendered_strip'] : FALSE;
          $grouping = $group_content = '';
          // Group on the rendered version of the field, not the raw.  That way,
          // we can control any special formatting of the grouping field through
          // the admin or theme layer or anywhere else we'd like.
          if (isset($this->view->field[$field])) {
            $group_content = $this->get_field($index, $field);
            if ($this->view->field[$field]->options['label']) {
              $group_content = $this->view->field[$field]->options['label'] . ': ' . $group_content;
            }
            if ($rendered) {
              $grouping = $group_content;
              if ($rendered_strip) {
                $group_content = $grouping = strip_tags(htmlspecialchars_decode($group_content));
              }
            }
            else {
              $grouping = $this->get_field_value($index, $field);
              // Not all field handlers return a scalar value,
              // e.g. views_handler_field_field.
              if (!is_scalar($grouping)) {
                $grouping = md5(serialize($grouping));
              }
            }
          }

          // Create the group if it does not exist yet.
          if (empty($set[$grouping])) {
            $set[$grouping]['group'] = $group_content;
            $set[$grouping]['rows'] = array();
          }

          // Move the set reference into the row set of the group we just determined.
          $set = &$set[$grouping]['rows'];
        }
        // Add the row to the hierarchically positioned row set we just determined.
        $set[$index] = $row;
      }
    }
    else {
      // Create a single group with an empty grouping field.
      $sets[''] = array(
        'group' => '',
        'rows' => $records,
      );
    }

    // If this parameter isn't explicitely set modify the output to be fully
    // backward compatible to code before Views 7.x-3.0-rc2.
    if ($group_rendered === NULL) {
      $sets = $this->handle_legacy_grouping($sets);
    }

    // Apply the offset and limit.
    $output = $this->group_limit_recursive($sets);
   
    return $output;
  }

  /**
   * Recursively limits the number of rows in nested groups.
   *
   * @param array $sets
   *   An array of grouped records, having a "rows" key.
   *
   * @return array
   *   The grouped records, limited by the specified limit and offset.
   */
  function group_limit_recursive($sets) {
    array_walk($sets, array($this, '_group_limit_recursive'));
    return $sets;
  }

  /**
   * Helper function for group_limit_recursive().
   *
   * @param array $group_data
   *   A single level of grouped records.
   *
   * @param mixed $key
   *   The key of the array being passed in. Used for when this function is
   *   called from array_walk() and the like. Do not set directly.
   *
   * @params int $level
   *   The current level we are gathering results for. Used for recursive
   *   operations; do not set directly.
   *
   * @return array
   *   An array with a "rows" property that is recursively grouped by the
   *   grouping fields.
   */
  function _group_limit_recursive(&$group_data, $key = NULL, $level = 0) {
    $settings = $this->grouping_limit_settings($level);

    // Slice up the rows according to the offset and limit.
    $group_data['rows'] = array_slice($group_data['rows'], $settings['grouping-offset'], $settings['grouping-limit'], TRUE);
   
    // For each row, if it appears to be another grouping, recurse again.
    foreach ($group_data['rows'] as $group => $data) {
      if (is_array($data) && isset($data['group']) && isset($data['rows'])) {
        $group_data['rows'][$group] = $this->_group_limit_recursive($data, NULL, $level + 1);
      }
    }
  }

  /**
   * Helper function to retrieve settings for grouping limit.
   *
   * @param int $index
   *   The grouping level to fetch settings for.
   *
   * @return array
   *   Settings for this grouping level.
   */
  function grouping_limit_settings($index) {
    return $this->options['grouping'][$index]['grouping-limit'];
  }

  /**
   * Helper function to handle legacy grouping style.
   *
   * @param array $sets
   *   The grouped items.
   *
   * @return array
   *   The grouped items, in pre-Views-7.x-3.0 style.
   */
  function handle_legacy_grouping($sets) {
    $legacy = array();

    foreach ($sets as $group) {
      $legacy[$group['group']] = $group['rows'];
    }

    return $legacy;
  }
}

/**
 * Validate the added form elements.
 */
function grouping_validate($element, &$form_state) {
  // Checking to see if numeric.
  if(!is_numeric($element['#value'])) {
    form_error($element, t('%element must be numeric.', array('%element' => $element['#title'])));
  }

  // Checking for negative values.
  if ($element['#value'] < 0) {
    form_error($element, t('%element cannot be negative.', array('%element' => $element['#title'])));
  }
}
