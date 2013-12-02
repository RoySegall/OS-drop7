<?php
// $Id$


/**
 * @file
 * os_dataverse.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function os_dataverse_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  /* Edit this to true to make a default context disabled initially */
  $context->disabled = FALSE;
  $context->api_version = 3;
  $context->name = 'dataverse_dataverse';
  $context->description = '';
  $context->tag = 'OS features';
  $context->conditions = array(
    'menu' => array(
      'values' => array(
        'data' => 'data',
      ),
    ),
    'path' => array(
      'values' => array(
        'data' => 'data',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('OS features');
  $export['dataverse_dataverse'] = $context;

  return $export;
}

