//Кольцевой буфер
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

constexpr uint16_t PERIOD_MS{1'000};

void blink_LED() {
    if (timer_get_counter(TIM1) < (PERIOD_MS / 2)) gpio_set(GPIOE,GPIO9);
    else gpio_clear(GPIOE, GPIO9);

}

void LED_gpio_setup () {
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9 | GPIO11 | GPIO14);

} 

void timer_setup () {
    rcc_periph_clock_enable(RCC_TIM1);

    timer_set_prescaler(TIM1, rcc_get_timer_clk_freq(TIM1) / PERIOD_MS - 1);
    timer_set_period(TIM1, PERIOD_MS - 1);

    timer_enable_counter(TIM1);
 }

int main (){

    //Настройка тактовой подсистемы
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);

    LED_gpio_setup(); 
    timer_setup();


    //Настройка порта ввода-вывода
    //rcc_periph_clock_enable(RCC_GPIOE);
    //gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9);

    while (true){
        //Переключение светодиода
        //gpio_toggle(GPIOE, GPIO9);
        //for (volatile uint32_t i = 0; i < 500'000; ++i);
        blink_LED();
    }
}  