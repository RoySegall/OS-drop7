<?php

/**
 * @file
 * Provides function to be run in behat test.
 */

/**
 * Attempts to load every box on the site.
 *
 * @return mixed
 *   If no boxes returned output, then the test passed. Returns ''.
 *   If at least one box was loaded, returns the (string) plugin key of the box.
 */
function _os_boxes_test_load_all_boxes_outside_vsite_context() {
  // Loads all existing box overrides.
  $query = db_select('spaces_overrides', 'so');
  $query->fields('so', array('value'));
  $query->condition('object_type', 'boxes');
  $result =$query->execute();

  // Looks individually at each overridden box...
  while ($record = $result->fetchAssoc()) {
    // Attempts to load the box object...
    $value = $record['value'];
    $box = unserialize($value);
    $box = boxes_box_load($box->delta);
    $key = isset($box->plugin_key) ? $box->plugin_key : FALSE;
    if ($key === FALSE) {
      // @todo can't seem to check user-generated boxes with id's like 12341234.
//      $pattern = '/delta.*?i:(?<delta>.*?);/';
//      $subject = $value;
//      $matches = array();
//      $found = preg_match($pattern, $subject, $matches);
//      if ($found && isset($matches['delta']) && strlen($matches['delta'])) {
//        $delta = $matches['delta'];
//        $box = boxes_box_load($delta);
//        $key = isset($box->plugin_key) ? $box->plugin_key : FALSE;
//      }
//      else {
//        continue;
//      }
      if ($key === FALSE) {
        continue;
      }
    }
    // Ignores sitewide boxes.
    if ($key === 'simple') {
      continue;
    }

    // Prevents undefined method error.
    if (!method_exists($box, 'render')) {
      continue;
    }

    // Checks that this box returns no content when loaded like this,
    // outside of a vsite spaces context.
    $render = $box->render();
    if ($render) {
      return $key;
    }
  }

  // Only gets to this point if all boxes displayed no content.
  return '';
}