<?php
/**
 * @file
 * Triggering the process of populating the field title attached to the
 * content type publications.
 */

$nid = drush_get_option('nid') ? drush_get_option('nid') : 0;

$i = 0;
$batch = 250;
while ($i < $batch) {
  $query = new EntityFieldQuery();
  $results = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'biblio')
    ->propertyCondition('nid', $nid, '>=')
    ->range($i, $i + $batch)
    ->execute();

  if (empty($results['node'])) {
   return;
  }

  // We found items to process.
  $ids = array_keys($results['node']);
  title_field_replacement_init('node', 'biblio', 'title', $ids);
  $nid = end($ids);
  ++$i;

  if (drupal_is_cli()) {
    // Display message when running the update via drush.
    $params = array(
      '@start' => reset($ids),
      '@end' => end($ids),
    );
    drush_log(dt('Replaced title with field instance for publication number @start to @end', $params), 'success');
  }
}
