<?php
// $Id$

/**
 * Create the processor that will override the purl_domain
 */
if (!class_exists('purl_vsite_domain')) {

  /**
   *  Full domain handling for scholar, will also remove purl prefix's from alias's
   */
  class purl_vsite_domain extends purl_domain implements purl_processor {

    public $modifier_regex = '!^[a-z0-9_\.-]+$!';

    /**
     * Simply matches our 'q' (aka domain) against an allowed value.
     *
     * If none is found and $q starts with www. then try without
     */
    public function parse($valid_values, $q) {
      $path_elements = parent::parse($valid_values, $q);

      if (!count($path_elements) && strpos($q, 'www.') === 0) {
        // Removes "www"
        $q = substr($q, 4);
        $path_elements = parent::parse($valid_values, $q);
      }

      return $path_elements;
    }

    function detect($q) {
      $plugin = ctools_get_plugins('spaces', 'plugins', 'vsite');
      if ($plugin) {
        $class = ctools_plugin_get_class($plugin, 'handler');
      }

      if (isset($class) && call_user_func(array($class, 'is_excluded_path'), $q)) {
        global $base_url;
        // Matches based on global base URL
        return $base_url;
      }
      else {
        $domain = parent::detect($q);

        // Removes the port if it is 80 (some browsers don't do this by default)
        if (substr($domain, -3) == ":80") {
          $domain = substr($domain, 0, (strlen($domain) - 3));
        }

        return $domain;
      }
    }

    public function method() {
      return PURL_VSITE_DOMAIN;
    }

    public function description() {
      return t('Enter a domain registered for this scholar site, such as "www.example.edu".  Do not include http://');
    }

    private function remove_scholar_purl($path, &$options) {
      if (!($vsite = spaces_get_space()) || !strlen($vsite->group->purl)) {
        return $path;
      }

      // Removes URL prefix if prefix is part of the path alias
      if (!empty($path) && $path != '<front>' && !$options['alias']) {
        $language = isset($options['language']) && isset($options['language']->language) ? $options['language']->language : '';

        //Get the stored alias.
        $alias = drupal_get_path_alias($path, $language);
        $args = explode('/', $alias);

        //If an alias exists and is prefixed with the purl value then remove it.
        if ($alias != $path && current($args) === (string) $vsite->group->purl) {
          // Removes the value from the front of the query string.
          array_shift($args);
          $options['alias'] = true;
          return implode('/', $args);
        }
      }

      return $path;
    }

    /**
     * Either force the url, or set it back to the base.
     */
    public function rewrite(&$path, &$options, $element) {
      $plugin = ctools_get_plugins('spaces', 'plugins', 'vsite');
      if ($plugin) {
        $class = ctools_plugin_get_class($plugin, 'handler');
      }
	  
      // Doesn't alter if link destination is an excluded path
      if (isset($class) && call_user_func(array($class, 'is_excluded_path'), $path)) {
        return;
      }

      $options['absolute'] = TRUE;
      if (!_purl_skip($element, $options)) {
        $path = $this->remove_scholar_purl($path, $options);
        $options['base_url'] = "http://{$element->value}";
      }
      else {
        global $base_url;
        $options['base_url'] = variable_get('purl_base_domain', $base_url);
      }
    }

    /**
     * If a purl_path/domain has been set we should rewrite the current url
     * so that aliased paths will be picked up
     */
    public function adjust(&$value, $item, &$q) {
      if ((!($vsite = spaces_get_space()) && !($vsite = spaces_load('og', $item->id))) || !strlen($vsite->group->purl)) {
        return;
      }
	  
      // Aliases query if it has not been aliased yet
      if (!in_array($vsite->group->purl, _vsite_domain_processed_purls())) {
        _vsite_domain_processed_purls($vsite->group->purl);

        $args = explode('/', trim($_GET['q'], '/'));

        // Prepends the value to the front of the query string
        if (current($args) !== (string) $vsite->group->purl) {
          array_unshift($args, $vsite->group->purl);
        }

        // String with purl added
        $qstring = implode('/', $args);
        // Alias of that url
        $qstring_alias = drupal_lookup_path('source', $qstring);

        // Modifies $q since purl/path/path has an alias
        if ($qstring_alias && $qstring != $qstring_alias) {
          $q = $qstring;
        }
      }
    }
  }
}

