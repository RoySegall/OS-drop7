<?php
// $Id$


/**
 * Return the pathauto settings modified to work inside vsites
 */
function _vsite_get_pathauto_settings() {
  $settings = array();

  // Prepends vsite purl to all group content node patterns.
  $bundles = array_keys(os_get_bundles(TRUE));
  $entity = 'node';
  foreach ($bundles as $bundle) {
    $pattern = pathauto_pattern_load_by_entity($entity, $bundle);
    $settings["pathauto_{$entity}_{$bundle}_pattern"] = "[vsite:site-purl]/" . $pattern;
  }
  // Prepends vsite purl to taxonomy term pattern.
  $pattern = pathauto_pattern_load_by_entity('taxonomy_term');
  $settings["pathauto_taxonomy_term_pattern"] = "[vsite:site-purl]/" . $pattern;

  return $settings;
}

/**
 * Integrates pathauto & purl for nodes.
 *
 * - Adds validation to verify paths without a purl prefix do not already exist,
 *   prevents collisions.
 *   i.e. If somehow a node is saved with a missing token for pathauto aliasing,
 *   in many cases, i.e. a blog without a title, the pathauto alias 'blog'
 *   for a node collides with the OS App menu item to list all blogs.
 *   In this case, we disable pathauto, and the node is saved like node/[nid].
 *
 * - Adds purl prefix to manually created paths to preserve namespace.
 *   i.e. A user Mary saves a Software Project with alias "mysoftware"
 *   Without this check here, now a sitewide alias "mysoftware" would exist,
 *   which would redirect to "mary/mysoftware".
 *
 * @see vsite_node_presave()
 */
function _vsite_alter_node_path_settings(&$node) {
  $vsite = vsite_get_vsite();
  if (!$vsite || ((int) $node->nid === (int) $vsite->group->nid)) {
    return;
  }
  module_load_include('inc', 'pathauto');
  $pattern = pathauto_pattern_load_by_entity('node', $node->type, $node->language);

  // For pathauto generated aliases, verify no naming collisions
  // Only checks aliases if a pathauto pattern exists and pathauto will alias.
  if ($pattern && (!(isset($node->path['pathauto']) && empty($node->path['pathauto'])))) {
    // Generates the pathauto alias and removes pURL modifiers
    $alias = _vsite_alias_without_purl($node);
    // Aborts pathauto for this node if the path already exists.
    if (_pathauto_path_is_callback($alias)) {
      $node->path['pathauto'] = 0;
      return;
    }
  }

  // For manually entered aliases, prefix alias with the purl modifier.
  // Note that Drupal has already validated the path prior to hook_node_presave,
  // so there's no way that an existing path has gotten to this point.
  else {
    $path = ltrim($node->path['alias'], "/");
    // Is there a valid path provided by the user?
    if (strlen($path) === 0) {
      return;
    }
    $no_purl_prefix = (strlen($vsite->group->purl) && (strpos($path, $vsite->group->purl . "/") !== 0));
    if ($no_purl_prefix) {
      $node->path['alias'] = $vsite->group->purl . "/" . $path;
    }
  }
}

/**
 * Integrates pathauto & purl for taxonomy terms.
 *
 * @see vsite_taxonomy_term_presave()
 * @see _vsite_alter_node_path_settings()
 */
function _vsite_alter_term_path_settings(&$term) {
  if (!$vsite = vsite_get_vsite()) {
    return;
  }
  module_load_include('inc', 'pathauto');
  $pattern = pathauto_pattern_load_by_entity('taxonomy_term');

  // For pathauto generated aliases, verify no naming collisions
  // Only checks aliases if a pathauto pattern exists and pathauto will alias.
  if ($pattern && (!(isset($term->path['pathauto']) && empty($term->path['pathauto'])))) {
    // Generates the pathauto alias and removes pURL modifiers
    $alias = _vsite_alias_without_purl($term, 'taxonomy_term');
    // Aborts pathauto for this node if the path already exists.
    if (_pathauto_path_is_callback($alias)) {
      $term->path['pathauto'] = 0;
      return;
    }
  }

  // For manually entered aliases, prefix alias with the purl modifier.
  // Note that Drupal has already validated the path prior to hook_node_presave,
  // so there's no way that an existing path has gotten to this point.
  else {
    $path = ltrim($term->path['alias'], "/");
    // Is there a valid path provided by the user?
    if (strlen($path) === 0) {
      return;
    }
    $no_purl_prefix = (strlen($vsite->group->purl) && (strpos($path, $vsite->group->purl . "/") !== 0));
    if ($no_purl_prefix) {
      $term->path['alias'] = $vsite->group->purl . "/" . $path;
    }
  }
}

/**
 * Returns the pathauto alias for a node, with any pURL modifiers removed.
 *
 * @param object $node
 *
 * @return string $alias
 *
 * @see _vsite_alter_node_path_settings()
 */
function _vsite_alias_without_purl($entity, $entity_type = 'node') {
  $uri      = entity_uri($entity_type, $entity);
  $language = !empty($entity->language) ? $entity->language : LANGUAGE_NONE;
  $bundle   = isset($entity->type) ? $entity->type : '';
  $alias    = pathauto_create_alias($entity_type, 'return', $uri['path'], array($entity_type => $entity), $bundle, $language);

  // Removes purl elements from alias string.
  $processor = purl_get_processor(PURL_VSITE_PATH);
  $elements = purl_parse($processor, $alias);
  foreach ($elements as $element) {
    $alias = $processor->remove($alias, $element);
  }

  return $alias;
}