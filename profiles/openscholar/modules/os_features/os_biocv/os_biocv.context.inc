<?php
/**
 * @file
 * os_biocv.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function os_biocv_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'biocv_biocv';
  $context->description = '';
  $context->tag = 'OS features';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'bio' => 'bio',
        'cv' => 'cv',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'path' => array(
      'values' => array(
        'biocv' => 'biocv',
        'biocv/*' => 'biocv/*',
        'bio' => 'bio',
        'bio/*' => 'bio/*',
      ),
    ),
  );
  $context->reactions = '';
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('OS features');
  $export['biocv_biocv'] = $context;

  return $export;
}
