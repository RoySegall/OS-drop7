<?php
// $Id$


/**
 * VSite space object
 *
 * @author rbrandon
 *
 * @todo Check Node Access
 * @todo Change Private Site handler
 * @todo Change Access Admin to work using permissions
 *
 */
class vsite extends space_og {

  // Stores the current provider.
  // Allows for a multi-provider system.
  public $purl_provider = FALSE;

  // Provides our own states different from the default Disabled/Enabled
  function feature_options() {
    return array(
      0 => t('Disabled'),
      1 => t('Public'),
      2 => 'Private',
    );
  }

  /**
   * Returns the absolute URL to this vsite
   */
  public function get_absolute_url($path = "") {
    // If this is an inactive site get the homepage path from the group node
    if ($this->active && !$this->purl_provider) {}
    elseif (!$this->purl_provider) {
      self::verify_purl();
    }

    return url($path, array(
        'purl' => array(
          'provider' => $this->purl_provider,
          'id' => $this->id,
        ),
        'absolute' => TRUE,
      ));
  }

  /**
   * Overrides activate().
   */
  function activate() {

    //Check if the current user has access to activate this space.
    if(!$this->access_space()){
      module_invoke_all('vsite_access_denied',$this);
      drupal_access_denied();
      drupal_exit();
    }

    // Test purl paths
    $this->activate_purl_modifier();

    if (parent::activate()) {
      // Sets up user roles (call before menu_get_item caches access info)
      $this->activate_user_roles();

      $router_items = &drupal_static('menu_get_item');
      // Have the menu access params already been set?
      if (isset($router_items[$_GET['q']])) {
        // If the current menu item may rely on the space so we reset the cached access information
        unset($router_items[$_GET['q']]);
      }

      return TRUE;
    }

    return FALSE;
  }

  /**
   * Deactivate Space
   */
  function deactivate(){
    // If variable controller had been init'ed reset it.
    // This prevent overridden variables from interacting
    // with the page.
    if(isset($this->controllers->variable)){
      global $conf;
      $conf = $this->controllers->variable->get(NULL,'original');
    }

    parent::deactivate();
  }

  /**
   * Implements space->router().
   */
  public function router($op, $node = NULL) {
    global $user;
    switch ($op) {
      case 'node':
        // If we are viewing the group node
        if (og_is_group_type('node', $node->type)) {
          if (isset($node->nid) && (!(isset($this->active) && $this->active) || ($this->active && $this->id != $node->nid)) && $space = spaces_load('og', $node->nid)) {
            // Sets up the correct purl provider
            $space->verify_purl();
            $current_url = url($_GET['q'], array(
                'absolute' => TRUE,
                'query' => drupal_get_query_parameters(),
              ));
            // Goto vsite's home <front> page
            if ($current_url != rtrim($space->get_absolute_url(), "/")) {
              purl_goto("<front>", array(
                  'purl' => array(
                    'provider' => $space->purl_provider,
                    'id' => $space->id,
                  ),
                ));
            }
          }
        }
        break;

      case 'init':
        if(!$this->active) {
          break;
        }

        // Redirects to path without purl for vsites with custom domains.
        if ($this->purl_provider == 'vsite_domain') {
          $path = _purl_cache_q();
          $path_parts = explode('/', $path);
          $index = array_shift($path_parts);
          if ($index == $this->group->purl) {
            // Redirects to the path with the purl prefix removed.
            if (!empty($path_parts)) {
              $path_without_purl = implode('/', $path_parts);
              purl_goto($path_without_purl, array(), 301);
            }
            // Redirects to vsite's home <front> page.
            else {
              purl_goto("<front>", array(
                  'purl' => array(
                      'provider' => $this->purl_provider,
                      'id' => $this->id
                  )
              ));
            }
          }
        }

        // Redirects to a node alias.
        if ($node = menu_get_object()) {
          if (isset($node->nid) && !og_is_group_type('node', $node->type)) {
            // First, redirects if this node does not belong to this vsite,
            // or if the request URL did not specify a vsite
            $wrapper = entity_metadata_wrapper('node', $node);
            $sids = $wrapper->{OG_AUDIENCE_FIELD}->value(array('identifier' => TRUE));
            $sid = isset($sids[0]) ? $sids[0] : NULL;
            // Handles both types of requests:
            // "node/123" and "wrongsite/node/123"
            if ((!$this->active && $sid) || ($sids && !in_array((int) $this->id, $sids))) {
              // Redirects to the correctly aliased node in its own vsite.
              spaces_load('og', $sid)->activate();
            }
            if (!$this->active) {
              break;
            }

            // Preventing a redirect loop when a node don't have an alias.
            if (!drupal_lookup_path('alias', $_GET['q'])) {
              break;
            }

            // Then, looks to redirect to node aliases if they exist.
            // This avoids a false redirect loop detection in purl_goto() when:
            //  - the path we are going to has an alias
            //  AND
            //  - the current page we are on does not use that alias value,
            $path = $_GET['q'];
            $aliased_path = url($path);
            $request_has_alias = (bool) ($path != $aliased_path);
            $path_parts = explode('/', _purl_cache_q());
            if ($request_has_alias && sizeof($path_parts) < 4) {
              // Handles both types of requests:
              // "mysite/node/123" AND "node/123" (on sites with custom domains)
              if ((sizeof($path_parts) == 3 && $path_parts[1] == 'node' && $path_parts[2] == $node->nid)
               || (sizeof($path_parts) == 2 && $path_parts[0] == 'node' && $path_parts[1] == $node->nid)) {
                // Redirects to the aliased node path.
                $path = $this->get_absolute_url("node/$node->nid");
                drupal_goto($path);
              }
            }
          }
        }
        break;
    }
    parent::router($op, $node);
  }

  /**
   * Overrides access_feature().
   */
  function access_feature($op = 'view', $feature, $account = NULL) {
    if ($feature == 'vsite' && $op == 'view' && user_access('access content')) {
      return TRUE;
    }

    // Check permission for the feed importer even if the os_reader is disabled.
    // When the reader app is disabled the content type feed_importer has access
    // denied. We need to make special validation for that.
    if ($feature == 'os_reader') {
      if ($_GET['q'] != 'node/add/feed-importer') {
        // Loading the node. Using the menu_get_path/object will cause recursion.
        $path = explode("/", $_GET['q']);
        if (isset($path[1])) {
          $node = node_load($path[1]);
          $check = is_object($node) && $node->type == 'feed_importer';
        }
        else {
          $check = FALSE;
        }
      }
      else {
        $check = TRUE;
      }
      if ($check) {
        return _os_reader_feed_importer_access_callback($op);
      }
    }

    $access = parent::access_feature($op, $feature, $account);

    // Checks feature 'privacy' settings
    $features = variable_get('spaces_features', array());
    if ($access && $features[$feature] > 1) {
      // Handles privacy levels that are not simple Public/Disabled
      switch ($features[$feature]) {
        // Private
        case 2:
          // Admin or group member?
          if (!og_is_member($this->group_type, $this->id, 'user', $account) && !user_access('administer nodes')) {
            $access = FALSE;
          }
          break;
        // Unknown Privacy Level
        default:
          $access = FALSE;
          break;
      }
    }

    // Additional check for private sites.
    return $access && node_access('view', $this->group, $account);
  }

  /**
   * verify_purl()
   *
   * If this space is loaded outside a active context (ie externally from the
   * home page), then determine which purl_provider would be best domain if they
   * have that set otherwise path.
   */
  protected function verify_purl() {
    $domain_method = variable_get('purl_method_vsite_domain', FALSE);
    if ($domain_method) {
      $elements = purl_active()->get($domain_method);
      foreach ($elements as $element) {
        if ($element->provider == "vsite_domain" && $element->id == $this->id) {
          $this->purl_provider = "vsite_domain";
          return TRUE;
        }
      }
    }

    $method = variable_get("purl_method_spaces_{$this->type}", 'path');
    $elements = purl_active()->get($method);
    foreach ($elements as $element) {
      if ($element->provider == "spaces_{$this->type}" && $element->id == $this->id) {
        $this->purl_provider = "spaces_{$this->type}";
        return TRUE;
      }
    }

    // No provider is active, lookup from id so redirection works.
    // Returns FALSE if we have reached here.
    $valid_providers = db_select('purl', 'purl')->fields('purl', array(
        'provider',
      ))->condition('id', $this->id, '=')->execute()->fetchCol();

    if (in_array('vsite_domain', $valid_providers)) {
      // This site has a domain provider.
      $this->purl_provider = 'vsite_domain';
    }
    // Otherwise, sets value from db
    elseif (in_array("spaces_{$this->type}", $valid_providers)) {
      // This site has a default provider.
      $this->purl_provider = "spaces_{$this->type}";
    }

    return FALSE;
  }

  /**
   * Overrides excluded_paths().
   *
   * The parent exlcudes 'features' and 'features/*'
   * We want them back
   */
  protected static function excluded_paths() {
    $excluded = parent::excluded_paths();

    unset($excluded[array_search('features', $excluded)]);
    unset($excluded[array_search('features/*', $excluded)]);

    $more = array(
      'user',
      'user/*',
      'users/*',
      'private_site',
      'help/*',
      'site/register',
      'welcome',
      'contact',
      'admin',
      'admin/*',
      'pinserver/auth',
      'pinserver/error/*',
      // 'files/*', Need files menu entry to be loaded in a space so that the purl can be used to serve old file pats. -RB
    );

    $excluded = array_merge($excluded, $more);
    return $excluded;
  }

  /**
   * Checks to see if a path is excluded.
   *
   * @param string $q
   * @return bool
   */
  public static function is_excluded_path($q) {
    $paths = implode("\n", self::excluded_paths());
    return drupal_match_path($q, $paths) ? TRUE : FALSE;
  }

  /**
   * Ensures pURL modifier is present, otherwise redirects via purl_goto()
   */
  protected function activate_purl_modifier() {
    if (!$this->verify_purl()) {
      $this->purge_request_destination();

      // Identical to spaces_purl_provider, but with dynamic provider.
      // @see spaces_purl_provider()
      if ($this->purl_provider) {
        // Sets the provider to use for redirection
        $options = array(
          'query' => drupal_get_query_parameters(),
          'purl' => array(
            'provider' => $this->purl_provider,
            'id' => $this->id,
          ),
        );
        $path = $_GET['q'];

        // Redirects with drupal_goto() if requested path has an alias.
        //
        // This avoids a false redirect loop detection in purl_goto() when:
        // * the path we are going to has an alias, AND
        // * the current page we are on does not use that alias value,
        // Example:
        // $_purl_cache_q will be "node/123" for both the aliased and
        // non-aliased paths
        $aliased = url($path);
        $_purl_cache_q = _purl_cache_q();
        if ($path != $aliased && isset($_purl_cache_q) && $path == $_purl_cache_q) {
          $path = $this->get_absolute_url($path);
          drupal_goto($path);
        }

        // Otherwise, redirects with purl_goto.
        purl_goto($path, $options);
      }
    }
  }

  /**
   * Activates user and modify roles based on the space.
   */
  protected function activate_user_roles() {
    global $user;

    $og_roles = og_get_user_roles($this->group_type, $this->id, $user->uid, FALSE);
    $drupal_roles = user_roles(TRUE);

    // Gets drupal core roles with the same name
    $common_roles = array_intersect($drupal_roles, $og_roles);

    foreach ($common_roles as $role) {
      $rid = array_search($role, $drupal_roles);
      $user->roles[$rid] = $role;
    }

    // Clears any staticly cached permissions
    drupal_static('user_access', NULL, TRUE);
  }

  /**
   * Overrides access_space().
   */
  function access_space($account = NULL) {
    return parent::access_space($account) && node_access('view', $this->group, $account);
  }
}

