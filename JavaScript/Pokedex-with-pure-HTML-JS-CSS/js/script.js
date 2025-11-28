
// Global Variables


const pokemonName = document.querySelector('.pokemon__name');
const pokemonNumber = document.querySelector('.pokemon__number');
const pokemonImage = document.querySelector('.pokemon__image');
const form = document.querySelector('.form');
const inputSearch = document.querySelector('.input__search');
const btnPrev = document.querySelector('.btn-prev');
const btnNext = document.querySelector('.btn-next');

let searchPokemon = 1;

// Functions

// API Function
const fetchPokemon = async (pokemon) => {
    const APIResponse = await fetch(`https://pokeapi.co/api/v2/pokemon/${pokemon}`);
    if(APIResponse.status === 200){
        const data = await APIResponse.json();
        return data;
    }
}

// Render Function
const renderPokemon = async (pokemon) => {
    pokemonName.innerHTML = 'Loading...'
    pokemonNumber.innerHTML = '';
    const data = await fetchPokemon(pokemon);
    if(data){
    pokemonName.innerHTML = '- '+data.name;
    pokemonNumber.innerHTML = data.id;
    pokemonImage.src = data['sprites']['versions']['generation-v']['black-white']['animated']['front_default'];
    inputSearch.value = '';
    searchPokemon = data.id;
    }else{
        pokemonName.innerHTML = 'Pokemon Unknown';
        pokemonNumber.innerHTML = '';
        pokemonImage.style.display = 'none';
    }
}

// Search Box Function
form.addEventListener('submit', (event) => {
    event.preventDefault();
    renderPokemon(inputSearch.value.toLowerCase());
}); 

// Button Prev Function
btnPrev.addEventListener('click', () => {
    if (searchPokemon > 1){
        searchPokemon -= 1;
    renderPokemon(searchPokemon);
    }
}); 

// Button Next Function
btnNext.addEventListener('click', () => {
    searchPokemon += 1;
    renderPokemon(searchPokemon);
}); 

renderPokemon(searchPokemon);