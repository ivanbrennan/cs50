module Visitable
  def accept(visitor)
    visitor.visit(self)
  end
end

class Wheel
  include Visitable

  attr_reader :name

  def initialize(name)
    @name = name
  end
end

class Engine
  include Visitable
end

class Body
  include Visitable
end

class Car
  include Visitable

  def initialize
    @elements = [
      Wheel.new('front left'),
      Wheel.new('front right'),
      Wheel.new('back left'),
      Wheel.new('back right'),
      Body.new,
      Engine.new
    ]
  end

  def accept(visitor)
    @elements.each { |e| e.accept(visitor) }
    super
  end
end

module CarElementVisit
  # required methods
  %i(
    visit_wheel
    visit_engine
    visit_body
    visit_car
  ).each do |method|
    define_method(method) { |*args| raise(NoMethodError, "Please implement #{method}") }
  end

  def visit(element)
    visit_method = visit_method_for(element)
    send(visit_method, element)
  end

  private

  def visit_method_for(element)
    case element
    when Wheel  then :visit_wheel
    when Engine then :visit_engine
    when Body   then :visit_body
    when Car    then :visit_car
    else raise(NotImplementedError, ":visit not implemented for #{element.class}")
    end
  end
end

module CarElementPrintVisitor
  extend CarElementVisit

  class << self
    def visit_wheel(wheel)
      puts("Visiting #{wheel.name} wheel")
    end

    def visit_engine(engine)
      puts('Visiting engine')
    end

    def visit_body(body)
      puts('Visiting body')
    end

    def visit_car(car)
      puts('Visiting car')
    end
  end
end

module CarElementDoVisitor
  extend CarElementVisit

  class << self
    def visit_wheel(wheel)
      puts("Kicking my #{wheel.name} wheel")
    end

    def visit_engine(engine)
      puts('Starting my engine')
    end

    def visit_body(body)
      puts('Moving my body')
    end

    def visit_car(car)
      puts('Starting my car')
    end
  end
end

car = Car.new
car.accept(CarElementPrintVisitor)
car.accept(CarElementDoVisitor)
