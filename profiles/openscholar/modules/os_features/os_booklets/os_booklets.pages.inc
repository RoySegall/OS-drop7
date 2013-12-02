<?php
// $Id$

/**
 * @file
 * OpenScholar control panel looks here for feature settings form.
 */

/**
 * Provides settings form for this feature on the Control Panel.
 */
function os_booklets_settings() {

  $form = array();

  // This variable hides os_boxes_booktoc widget and output table of contents
  // instead in the full node page content.
  // @see os_boxes_booktoc::render()
  // @see os_booklets_node_view()
  $form['os_booklets_toc_position'] = array(
    '#type' => 'radios',
    '#title' => t('Table of contents position'),
    '#options' => array(
    	'0' => 'Display as a widget (default)',
    	'1' => 'Display inline at the top of book page content',
    ),
    '#default_value' => variable_get('os_booklets_toc_position', 0),
    '#required' => FALSE,
  );

  return system_settings_form($form);
}