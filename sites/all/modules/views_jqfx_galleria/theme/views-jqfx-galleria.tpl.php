<?php
/**
 * @file
 */
?>
<div id="views-jqfx-galleria-<?php print $id; ?>" class="views-jqfx-galleria">
  <div id="views-jqfx-galleria-images-<?php print $id; ?>" class="<?php print $classes; ?>">
    <?php foreach ($content as $image): ?>
      <?php print $image ."\n"; ?>
    <?php endforeach; ?>
  </div>
</div>
