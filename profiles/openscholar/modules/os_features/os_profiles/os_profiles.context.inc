<?php
// $Id$

/**
 * @file
 * os_profiles.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function os_profiles_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  /* Edit this to true to make a default context disabled initially */

  $context->disabled = FALSE;
  $context->api_version = 3;
  $context->name = 'profiles_profiles';
  $context->description = '';
  $context->tag = 'OS features';
  $context->conditions = array(
    'menu' => array(
      'values' => array(
        'people' => 'people',
      ),
    ),
    'node' => array(
      'values' => array(
        'person' => 'person',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'path' => array(
      'values' => array(
        'people' => 'people',
        'people/*' => 'people/*',
      ),
    ),
    'views' => array(
      'values' => array(
        'os_profiles' => 'os_profiles',
        'os_profiles:page' => 'os_profiles:page',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('OS features');
  $export['profiles_profiles'] = $context;

  return $export;
}

