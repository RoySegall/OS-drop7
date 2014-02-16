api = 2
core = 7.x
projects[drupal][type] = "core"
projects[drupal][version] = "7.23"
projects[drupal][download][type] = git
projects[drupal][download][tag] = "7.24"
projects[drupal][download][url] = http://git.drupal.org/project/drupal.git
projects[drupal][patch][] = "http://drupal.org/files/order-weighted-terms-941266-35-D7.patch"
projects[drupal][patch][] = "http://drupal.org/files/drupal-apc_redeclare_database-838744-24.patch"
projects[drupal][patch][] = "http://drupal.org/files/text-summary-word-break.patch"
projects[drupal][patch][] = "https://drupal.org/files/drupal.menu-theme-objects.18.patch"

