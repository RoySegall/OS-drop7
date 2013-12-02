<?php
// $Id$


/**
 * @file
 * os_publications.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os_publications_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_author_links';
  $strongarm->value = 0;
  $export['biblio_author_links'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_base';
  $strongarm->value = 'publications';
  $export['biblio_base'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_base_title';
  $strongarm->value = 'Publications';
  $export['biblio_base_title'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_contrib_fields_delta';
  $strongarm->value = '1';
  $export['biblio_contrib_fields_delta'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_export_links';
  $strongarm->value = array(
    'bibtex' => 'bibtex',
    'rtf' => 'rtf',
    'tagged' => 'tagged',
    'xml' => 'xml',
    'ris' => 'ris',
  );
  $export['biblio_export_links'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_init_auth_count';
  $strongarm->value = '1';
  $export['biblio_init_auth_count'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_rowsperpage';
  $strongarm->value = '20';
  $export['biblio_rowsperpage'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_biblio';
  $strongarm->value = 0;
  $export['comment_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_biblio';
  $strongarm->value = 0;
  $export['comment_anonymous_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_biblio';
  $strongarm->value = 1;
  $export['comment_default_mode_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_biblio';
  $strongarm->value = '50';
  $export['comment_default_per_page_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_biblio';
  $strongarm->value = 1;
  $export['comment_form_location_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_biblio';
  $strongarm->value = '1';
  $export['comment_preview_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_biblio';
  $strongarm->value = 1;
  $export['comment_subject_field_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_biblio';
  $strongarm->value = array(
    0 => 'primary-menu',
    1 => 'secondary-menu',
  );
  $export['menu_options_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_biblio';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_biblio';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_biblio';
  $strongarm->value = '0';
  $export['node_preview_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_biblio';
  $strongarm->value = 1;
  $export['node_submitted_biblio'] = $strongarm;

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_biblio_pattern';
  $strongarm->value = 'publications/[node:title]';
  $export['pathauto_node_biblio_pattern'] = $strongarm;

  return $export;
}

