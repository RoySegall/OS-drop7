<?php

/**
* @file
* Definition of html_title_handler_field_node_title class.
*/

/**
 * Override the standard node title rendering to enable select HTML tags.
 */
class html_title_handler_field_node_title extends views_handler_field_node {

  /**
  * Renders the field handler.
  */
  function render($values) {
    $output = parent::render($values);

    $elements = variable_get('html_title_allowed_elements', array('em', 'sub', 'sup'));
    if (count($elements)) {
      static $done = false;

      // Ensure this block executes only once
      if (!$done) {

        // Add permitted elements to options so they are not stripped later
        $tags = array();
        foreach ($elements as $element) {
          $tags[] = '<'. $element .'>';
        }
        $this->options['alter']['preserve_tags'] .= ' '. implode(' ', $tags);
        $done = true;
      }

      // Decode permitted HTML elements
      $pattern = "/&lt;(\/?)(". implode('|', $elements) .")&gt;/i";
      return preg_replace($pattern, '<$1$2>', $output);
    }

    return $output;
  }
}
