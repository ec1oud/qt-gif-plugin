# qt-gif-plugin
Alternative GIF imageformat plugin which uses giflib, supports reading and writing, and GIF comments.

Qt 4.5.x already has a GIF imageformat plugin, implemented in a self-contained way; however it can only read GIFs. This one is an alternative which can both read and write GIFs. It is simply a wrapper for giflib. It also supports GIF comments for both reading and writing, via QImage::text, setText or QImageWriter::setText.

The usual reason for not implementing GIF writing capabilities was because of the annoying old Unisys-owned patents, but those have now expired. Nobody much cares for GIF anymore, but it's occasionally useful to prepare GIF images for old software which does not support PNG. Futhermore the Qt PNG and JPEG plugins do not yet support preserving comments as metadata within the image, so it's an improvement to have available a format which does.

The original motivation for this plugin is to enable GIF export from PDFs, while embedding the OCR'd text as a GIF comment.

See the related project for which this has been used: https://sourceforge.net/projects/taborca/
