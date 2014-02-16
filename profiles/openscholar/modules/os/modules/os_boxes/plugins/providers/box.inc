<?php

$plugin = array(
  'title' => 'Box',
  'capture subpatterns' => TRUE,
  'scheme' => '*/box/*',
  'callback' => 'os_boxes_box_provider',
  'provider' => TRUE,
  'consumer' => TRUE
);


/**
 * Default provider for boxes
 */
function os_boxes_box_provider($plugin, $url, $matches, $parameters) {

  $result = FALSE;
  if ($matches[1] == $GLOBALS['base_url']) {
    list($purl, $delta) = explode('/', $matches[2]);
    if (!$delta) {
      // single tenant site
      $delta = $purl;
    }
    else {
      // multi tenant site
      // activate the space
      purl_get_normal_path($purl, true);
    }

    $defaults = array('view_mode' => 'full', 'langcode' => NULL);
    $parameters = array_merge($defaults, $parameters);
    $box = boxes_box_load($delta);

    if ($box) {

      $block = $box->render();

      $result = array(
        'type' => 'rich',
        'html' => $block['content'],
        'title' => $box->title,
        'widget_type' => $box->plugin_key
      );
      $result = _oembedprovider_result($result['type'], $result);
    }
  }
  else {
    $plugin['endpoint'] = $matches[1].'/oembed/endpoint';
    $function = ctools_plugin_load_function('oembed', 'providers', 'default', 'callback');
    $result = call_user_func($function, $plugin, $url, $matches, $parameters);
  }

  return $result;
}