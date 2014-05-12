
class Mergesort

  def self.sort array=[], origlength=nil
    length = array.size
    origlength = origlength.nil? ? length : origlength

    if length < 2
      return array
    end

    prefix = length.nil? ? "" :
      "-"*( origlength / (length/origlength.to_f * 10).ceil + 1 )


    a = array[0..(length/2-1)]
    b = array[(length/2)..-1]
    c = []

    puts "#{prefix} #{a[0]}(a)"
    puts "#{prefix} #{b[0]}(b)"

    a = self.sort a, origlength
    b = self.sort b, origlength

    i = 0
    j = 0
    (0..length).each do |k|
      if a[i].nil? and b[j].nil?
        puts "#{c}"
        return c
      elsif b[j].nil?
        c << a[i]
        i = i + 1
      elsif a[i].nil?
        c << b[j]
        j = j + 1
      elsif a[i] < b[j]
        c << a[i]
        i = i + 1
      elsif b[j] < a[i]
        c << b[j]
        j = j + 1
      end
    end
  end

end
