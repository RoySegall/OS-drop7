<?php

/**
 * @file
 * Hooks provided by the OG Tasks module.
 */

/**
 * Implements hook_og_tasks_info().
 *
 * @see OG Tasks example module.
 */
function hook_og_tasks_info($entity_type, $entity) {
  $tasks = array();

  $tasks['tasks_demo'] = new ogTasksExample($entity_type, $entity);

  return $tasks;
}
