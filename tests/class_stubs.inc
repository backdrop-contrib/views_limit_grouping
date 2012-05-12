<?php

/**
 * @file
 * Contains stubs for dependant classes.
 */

/**
 * Stub for views_plugin_style class, from the views module.
 */
class views_plugin_style {
  protected $view;

  function options_form(&$form, &$form_state) {}
  function render_grouping($records, $grouping, $group_rendered = NULL) {}
  function render_fields($items) {}

  function __construct() {
    $this->view = new StdClass();
    $this->view->result = array();
  }
}
