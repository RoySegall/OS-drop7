<?php

/**
 * @file
 *
 * This file contains no working PHP code; it exists to provide additional documentation
 * for doxygen as well as to document hooks in the standard Drupal manner.
 */

/**
 * Register JS callbacks. Read the documentation for a detailed explanation
 *
 * @return array
 *   An array of callbacks with the following possible keys for each callback:
 *   - callback: (required) The function to call to display the results when an ajax call occurs on this path
 *   - includes: (optional) Load aditional files from the /includes directory, without the extension
 *   - dependencies: (optional) Load additional modules for this callback
 *   - bootstrap: (optional) The bootstrap level Drupal should boot to, defaults 
 *                to DATABASE or SESSION if an access argument/callback is defined
 *   - file: (optional) In which file the callback function is defined
 *   - access arguments: (optional) Arguments for the access callback
 *   - access callback: (optional) Callback for the access check, default to 
 *                      user_access if there is an acces argument defined
 *   
 */
function hook_js() {
  return array(
    'somefunction' => array(
      'callback' => 'example_somefunction',
      'includes' => array('includefile1', 'includefile2'),
      'dependencies' => array('module1', 'module2'),
      'file'         => 'includes/example.inc',
      'bootstrap'    => DRUPAL_BOOTSTRAP_CONSTANT,
      'access arguments' => array('e.g. permission'),
      'access callback'  => 'callback function'
    ),
  );
}
