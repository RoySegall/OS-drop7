<?php
// $Id$

/**
 * @file
 * Message to display to admin if bio has not been created yet for this site.
 */
?>
<div id="os-biocv-bio-block-empty-text">
  <?php if (!empty($message)): ?>
    <p>
      <?php print $message; ?>
    </p>
  <?php endif; ?>
</div>

