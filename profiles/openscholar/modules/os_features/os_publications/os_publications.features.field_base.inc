<?php
/**
 * @file
 * os_publications.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function os_publications_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_biblio_extra'
  $field_bases['field_biblio_extra'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_biblio_extra',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'dyntextfield',
    'settings' => array(
      'size' => 60,
    ),
    'translatable' => 0,
    'type' => 'dyntextfield',
  );

  // Exported field_base: 'field_biblio_image'
  $field_bases['field_biblio_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_biblio_image',
    'foreign keys' => array(
      'fid' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  // Exported field_base: 'title_field'
  $field_bases['title_field'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'title_field',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 1,
    'type' => 'text_long',
  );

  return $field_bases;
}
