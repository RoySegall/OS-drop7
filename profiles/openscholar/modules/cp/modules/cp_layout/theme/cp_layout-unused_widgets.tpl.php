<!-- Do something about tabs and factories -->
<?php
echo $factory_html;
if (count($tags) > 0) { ?>
	<ul id="widget-categories"><?php
  foreach ($tags as $t) {
    ?>
    <li><a href="#<?php echo $t; ?>"><?php echo $t; ?></a></li>
    <?php
  }
  ?></ul><?php
}
?>
<div id="edit-layout-unused-widgets">
  <div class="widget-container">
<?php
echo $children;
?>
  </div>
</div>
<div id="websiteLabelTab"></div>
