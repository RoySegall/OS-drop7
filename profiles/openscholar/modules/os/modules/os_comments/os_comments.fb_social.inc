<?php
/**
 * @file
 * os_comments.fb_social.inc
 */

/**
 * Implements hook_fb_social_default_presets().
 */
function os_comments_fb_social_default_presets() {
  $export = array();

  $fb_social_preset = new stdClass();
  $fb_social_preset->disabled = FALSE; /* Edit this to true to make a default fb_social_preset disabled initially */
  $fb_social_preset->api_version = 1;
  $fb_social_preset->name = 'Facebook Comments';
  $fb_social_preset->description = 'Facebook Post comments';
  $fb_social_preset->plugin_type = 'comments';
  $fb_social_preset->settings = array(
    'node_types' => array(
      'types' => array(
        'page' => 0,
        'biblio' => 0,
        'blog' => 0,
        'book' => 0,
        'event' => 0,
        'feed' => 0,
        'media_gallery' => 0,
        'news' => 0,
        'link' => 0,
        'software_project' => 0,
        'software_release' => 0,
      ),
    ),
    'plugin_location' => array(
      'node_view_modes' => array(
        'full' => 'full',
        'teaser' => 0,
        'rss' => 0,
        'search_index' => 0,
        'search_result' => 0,
        'print' => 0,
        'media_gallery_block' => 0,
        'token' => 0,
      ),
    ),
    'plugin_comments_count' => array(
      'count' => 1,
      'cache' => '30',
    ),
    'plugin_comments_seo' => array(
      'seo' => 0,
      'nr_comments' => '100',
      'cache_length' => '720',
    ),
    'block' => 0,
  );
  $fb_social_preset->fb_attrs = array(
    'numposts' => '10',
    'width' => '550',
    'colorscheme' => 'light',
    'migrated' => 0,
  );
  $export['Facebook Comments'] = $fb_social_preset;

  return $export;
}
