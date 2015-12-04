class Webcam
  attr_accessor :fmt, :capture_cb

  def bye
    self.hello + " bye"
  end

  def capture(&blk)
    @capture_cb = blk
  end

end
