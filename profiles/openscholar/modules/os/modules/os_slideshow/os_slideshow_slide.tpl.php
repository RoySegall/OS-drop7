<?php 
/**
 * Slides and their captions
 */

?>

<li>
  <?php print $image; ?>
  <?php if ($headline || $description): ?>
    <div class="caption slide-copy">
      <h2><?php print $headline; ?></h2>
      <p><?php print $description; ?></p>
    </div>
  <?php endif; ?>
</li>

